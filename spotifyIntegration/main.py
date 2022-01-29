import requests
import time
from threading import Thread
from pprint import pprint


SPOTIFY_GET_CURRENT_TRACK_URL = 'https://api.spotify.com/v1/me/player/currently-playing'
SPOTIFY_GET_TRACK_INFO_URL = 'https://api.spotify.com/v1/audio-analysis/'
ACCESS_TOKEN = 'BQCHPoeTyjz31W_NtkY-DKEKFT5vyC9pd5Wm2T5oMjEC5juR70hi5wm4Ncct8pgMhiQAQbkPjILHiqW484DWzdNrd8Mde6kPCfyUkt9al-h5iPGi9N1I_CV7dr3OKeoMiTCxhuuL4N6Jh1YWClkoTQJnF4rbng5rdcVcKuDkiBCtq0nd1A'

previous_track_id = ''
track_json_segments = []

# in ms
current_track_time = 0
current_local_time = 0
current_track_segment = 0

def spike(x, n):
    return 1 - abs((x - n*8.67)/4.941)

def get_color(j, loudness, pitches):
    pitches.append(pitches[0])
    return loudness* (pitches[int(j/8.67)] * spike(j, int(j/8.67)) + pitches[int(j/8.67)] * spike(j, int(j/8.67) + 1))

def get_current_segment():
    global current_track_segment
    temptime = current_track_time + current_local_time - time.time()
    left = 0
    right = len(track_json_segments) - 1
    if track_json_segments[current_track_segment]['start'] + track_json_segments[current_track_segment]['duration'] > temptime and track_json_segments[current_track_segment]['start'] < temptime:
        return
    if left == right:
        current_track_segment = left
        return 
    while True:
        mid = int((left + right)/2)
        if track_json_segments[mid]['start'] <= temptime:
            left = mid
            if track_json_segments[mid]['start'] + track_json_segments[mid]['duration'] > temptime:
                current_track_segment = mid
                break
        if track_json_segments[mid]['start'] > temptime:
            right = mid

def get_loudness():
    segment = track_json_segments[current_track_segment]
    if current_track_segment < len(track_json_segments) - 1:
        temptime = current_track_time + current_local_time - time.time()
        temp = 0
        if temptime < segment['loudness_max'] + segment['loudness_max_time']:
            temp = (temptime - segment['start']) * (segment['loudness_max'] - segment['loudness_start'])/segment['loudness_max_time'] + segment['loudness']
        else:
            segment2 = track_json_segments[current_track_segment + 1]
            temp = (temptime - segment['start'] - segment['loudness_max_time']) * (segment2['loudness_start'] - segment['loudness_max'])/(segment['duration'] - segment['loudness_max_time']) + segment['loudness_max']

        return (temp+60)/60
    else:
        return 0

def track_updater(access_token):
    global previous_track_id
    global track_json_segments
    global current_track_time
    global current_local_time

    while True:
        response = requests.get(
            SPOTIFY_GET_CURRENT_TRACK_URL,
            headers={
                "Authorization": f"Bearer {access_token}"
            }
        )
        if response.status_code != 200:
            print("bad user read ", response.status_code)
        if response.status_code == 200:
            json_resp = response.json()
            if json_resp == None:
                continue
            track_id = json_resp['item']['id']
            current_track_time = json_resp['progress_ms']/1000
            current_local_time = time.time()

            if previous_track_id != track_id:
                trackinfo = requests.get(
                    SPOTIFY_GET_TRACK_INFO_URL + track_id, 
                    headers={
                        "Authorization": f"Bearer {access_token}"
                    }
                ) 

                if trackinfo.status_code == 200:
                    track_json_segments = trackinfo.json()["segments"]
                    previous_track_id = track_id
                else: 
                    print("bad analysis read ", trackinfo.status_code)
        time.sleep(1)

def main(): 
    t = Thread(target=track_updater, args=[ACCESS_TOKEN])
    t.daemon = False
    t.start()
    while True: 
        if len(track_json_segments) > 0:
            get_current_segment()
            loud = get_loudness()
            get_color(0, loud, track_json_segments[current_track_segment]['pitches'])


if __name__ == '__main__':
    main()

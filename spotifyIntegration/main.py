import requests
import time

from pprint import pprint


SPOTIFY_GET_CURRENT_TRACK_URL = 'https://api.spotify.com/v1/me/player/currently-playing'
SPOTIFY_GET_TRACK_INFO_URL = 'https://api.spotify.com/v1/audio-analysis/'
ACCESS_TOKEN = 'BQCav-MNCUqWSWTGK_JsnvsF7fTZHHVH9LDnhzVbJtTJ-HpgumZ21-yOQA3LDYszJpkHKPQF_pOYF0PBYOxLY3pMYUVY1cDdhlGrRDj0ZuUzgJdEY7S92fYwNVPpa6sGgQg2I8_9kEycUfOQ-CRVLNoKDODof-_ZzqJUec7VBUFVRwiA2w'

previous_track_id = ''
track_json = {}
track_prev_loc = 0

def get_current_track(access_token):
    global previous_track_id
    global track_json 
    global track_prev_loc

    response = requests.get(
        SPOTIFY_GET_CURRENT_TRACK_URL,
        headers={
            "Authorization": f"Bearer {access_token}"
        }
    )
    current_track_info = {}
    pprint(response.status_code)
    if response.status_code == 200:
        json_resp = response.json()

        track_id = json_resp['item']['id']

        link = json_resp['item']['external_urls']['spotify']
        position = json_resp['progress_ms']

        current_track_info = {
            "link": link,
            "position": position
        }

        if previous_track_id != track_id:
            trackinfo = requests.get(
                SPOTIFY_GET_TRACK_INFO_URL + track_id, 
                headers={
                    "Authorization": f"Bearer {access_token}"
                }
            ) 
            
            pprint(trackinfo.status_code)
            if trackinfo.status_code == 200:
                track_json = trackinfo.json() 

        i = track_prev_loc
        while i < len(track_json['segments']) and position/1000 > track_json['segments'][i]['start'] + track_json['segments'][i]['duration']:
            i += 1 
                
        if i == len(track_json['segments']):
            i = 0 
            while i < len(track_json['segments']) and position/1000 > track_json['segments'][i]['start'] + track_json['segments'][i]['duration']:
                i += 1 

        track_prev_loc = i

        pprint(track_json['segments'][i])

    return current_track_info


def main():
    while True:
        current_track_info = get_current_track(ACCESS_TOKEN)

        pprint(
            current_track_info,
            indent=4,
        )


if __name__ == '__main__':
    main()

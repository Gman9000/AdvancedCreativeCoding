# shows artist info for a URN or URL

import configparser
from spotipy.oauth2 import SpotifyClientCredentials
from spotipy.oauth2 import SpotifyOAuth
import spotipy
import sys
import pprint

import argparse
from pythonosc import osc_message_builder
from pythonosc import udp_client
from pythonosc import dispatcher
from pythonosc import osc_server

#setupStuff
config = configparser.ConfigParser()
config.read('config.cfg')
client_id = config.get('SPOTIFY', 'CLIENT_ID')
client_secret = config.get('SPOTIFY', 'CLIENT_SECRET')
scope = "user-read-playback-state,user-modify-playback-state"
#i honestly don't know about redirect_uri yet but it works so whatever
redirect_uri='https://open.spotify.com/'
username='Dazzle'

#set a function to save the value
def handle_search_entry(*args):

    #print(args)
    search_str = args[1]
    
    sp = spotipy.Spotify(client_credentials_manager=SpotifyClientCredentials(
        client_id=client_id,
        client_secret=client_secret
    ))

    result = sp.search(q='track:' + search_str,limit=1, type='track')
    items = result['tracks']['items']

    ##we only need one result so we limit the results to one item
    if len(items) > 0:
        singleSongUri = items[0]['uri']

    #song analysis
    analysis = sp.audio_features(singleSongUri)



    #send this information back to my program
    client.send_message("/energy", analysis[0]['energy'])
    client.send_message("/tempo", analysis[0]['tempo'])
    client.send_message("/valence", analysis[0]['valence'])


    #UP TO HERE
    
    #this is for song playback
    sp = spotipy.Spotify(client_credentials_manager=SpotifyOAuth(
        scope=scope,
        client_id=client_id,
        client_secret=client_secret,
        redirect_uri=redirect_uri,
        username=username
    ))

    # plays the song but it's playing on my phone or whatever device is active at the time LOL
    sp.start_playback(uris=[singleSongUri])
# HANDLE SEARCH FUNCTION IS ABOVE



if __name__ == "__main__":
    #from python to visual studio is port 8080
    client = udp_client.SimpleUDPClient("127.0.0.1", 8080)

    #this is from visual studio to here and it needs to be port 8082
    dispatcher = dispatcher.Dispatcher()
    dispatcher.map("/userSearch", handle_search_entry)
    #dispatcher.map("/userSearch", print)
    server = osc_server.ThreadingOSCUDPServer(
        ("127.0.0.1", 8082), dispatcher)
    server.serve_forever()







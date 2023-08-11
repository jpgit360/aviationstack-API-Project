import requests
import json
import config # external file that holds api key

params = {
  'access_key': config.API_KEY,
}

api_result = requests.get('http://api.aviationstack.com/v1/flights', params)

api_response = api_result.json()

fakeapi_path = "../store/fakeapi.json"
ingest_path =  "../store/ingest.json"

'''#test code without having to make another api call
#-------------------------------------------------
with open(fakeapi_path, "r") as json_file:
    api_response = json.load(json_file)
#-------------------------------------------------'''


api_response.pop("pagination")

with open(ingest_path, "w") as outfile:
    json.dump(api_response, outfile, indent=2)


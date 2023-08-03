import requests
import json
import config # external file that holds api key

'''params = {
  'access_key': config.API_KEY,
}

api_result = requests.get('http://api.aviationstack.com/v1/flights', params)

api_response = api_result.json()'''


#test code without having to make another api call
#-------------------------------------------------
with open("fakeapi.json" ,"r") as json_file:
    api_response = json.load(json_file)
#-------------------------------------------------


api_response.pop("pagination")

with open("ingest.json", "w") as outfile:
    json.dump(api_response, outfile, indent=2)


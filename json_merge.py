import json

# open main json file (the one I'm merging into)
with open("all_data.json", "r") as master_json_file:
    # load json file into dictionary object
    master_json_dict = json.load(master_json_file)

# open newly ingested json file
with open("ingest.json" ,"r") as ingested_json_file:
    ingested_json_dict = json.load(ingested_json_file)

#test code
test = ingested_json_dict["data"][0]
master_json_dict["data"].append(test)

#create vector to store keys
ingest_keys = []

# loop through ingest dictionary and populate keys vector
for i in ingested_json_dict["data"]:
    departure_data = i["departure"]["iata"] if i["departure"]["iata"] else ""
    arrival_data = i["arrival"]["iata"] if i["arrival"]["iata"] else ""
    flightnum_data = i["flight"]["number"] if i["flight"]["number"] else ""
    str = departure_data + arrival_data + flightnum_data
    ingest_keys.append(str)

# merge to master_json_dict only if its key doesnt already exist in keys.csv
    # if key already exists, set the ingest_keys[i] to some sort of null value (None)
# after merged, append ingest_keys to keys.csv

with open("all_data.json", "w") as json_file:
    json.dump(master_json_dict, json_file, indent=2)


import json
import csv
import os

all_data_file = "C:/Users/jfpth/OneDrive/Desktop/aviationstack_api_project/all_data.json"
ingest_data_file = "C:/Users/jfpth/OneDrive/Desktop/aviationstack_api_project/data_ingestion/ingest.json"
key_data_file = "C:/Users/jfpth/OneDrive/Desktop/aviationstack_api_project/data_ingestion/keys.csv"

if os.path.getsize(all_data_file) == 0:
    print(f"{all_data_file} is empty.")
    master_json_dict = {"data": []}
else:
    try:
        # open all_data.json (the one I'm merging into)
        with open(all_data_file, "r") as master_json_file:
            # load json file into dictionary object
            master_json_dict = json.load(master_json_file)
    except json.JSONDecodeError as e:
        print(f"Error loading json: {e}")

if os.path.getsize(ingest_data_file) == 0:
    print(f"{ingest_data_file} is empty.")
    ingested_json_dict = {}
else:
    try:
        # open ingest.json
        with open(ingest_data_file ,"r") as ingested_json_file:
            ingested_json_dict = json.load(ingested_json_file)
    except json.JSONDecodeError as e:
        print(f"Error loading json: {e}")
    
#test code
#test = ingested_json_dict["data"][0]
#master_json_dict["data"].append(test)

#create vector to store keys
ingest_keys = []

# loop through ingest dictionary and populate keys vector
for i in ingested_json_dict["data"]:
    departure_data = i["departure"]["iata"] if i["departure"]["iata"] else ""
    arrival_data = i["arrival"]["iata"] if i["arrival"]["iata"] else ""
    flightnum_data = i["flight"]["number"] if i["flight"]["number"] else ""
    str = departure_data + arrival_data + flightnum_data
    ingest_keys.append(str)

# get all keys
if os.path.getsize(key_data_file) == 0:
    print(f"{key_data_file} is empty.")
    all_keys = []
else:
    with open(key_data_file, "r") as file:
        reader = csv.reader(file)
        all_keys = next(reader)

# merge to master_json_dict only if its key doesnt already exist in keys.csv
# if key already exists, set the ingest_keys[i] to None
for i in range(len(ingest_keys)):
    key = ingest_keys[i]
    if key in all_keys:
        ingest_keys[i] = None
    else:
        new_data = ingested_json_dict["data"][i]
        master_json_dict["data"].append(new_data)

print("ingest keys: ", ingest_keys)
# pop None values from ingest_keys
ingest_keys = list(filter(None, ingest_keys))
print("ingest keys after filter: ", ingest_keys)

# append updated keys to keys.csv
updated_keys = all_keys + ingest_keys
with open(key_data_file, "w") as file:
    writer = csv.writer(file)
    writer.writerow(updated_keys)

with open(all_data_file, "w") as json_file:
    json.dump(master_json_dict, json_file, indent=4)


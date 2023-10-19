import requests

def test_register_plant():
    headers = {"User-Agent": "ESP32 Client", "content-type": "application/x-www-form-urlencoded"} 
     
    try:
        r = requests.post("https://iwaterplant.000webhostapp.com/IWP_register_plant.php", data="device_id=101&plant_name=test_name&plant_id=3", headers=headers)
        
        print("Response code: ")
        print(r.status_code)
        print(r.text)
    except requests.exceptions.HTTPError as errh:
        print("HTTP error")
        print(errh.args[0])
        
test_register_plant()
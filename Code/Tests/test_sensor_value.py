import requests

def test_sensor_value():
    headers = {"User-Agent": "ESP32 Client", "content-type": "application/x-www-form-urlencoded"} 
     
    try:
        r = requests.post("https://iwaterplant.000webhostapp.com/IWP_process.php", data="device_id=101&sensor_value=24", headers=headers)
        
        print("Response code: ")
        print(r.status_code)
        print(r.text)
    except requests.exceptions.HTTPError as errh:
        print("HTTP error")
        print(errh.args[0])
    
test_sensor_value()
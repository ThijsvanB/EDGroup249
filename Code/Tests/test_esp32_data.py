import requests

def test_get_esp32data():
    try:
        r = requests.get("https://iwaterplant.000webhostapp.com/IWP_get_esp32data.php?device_id=101")
        
        print("Response code: ")
        print(r.status_code)
        print(r.text)
    except requests.exceptions.HTTPError as errh:
        print("HTTP error")
        print(errh.args[0])
        
test_get_esp32data()
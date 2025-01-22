import http.client, urllib
conn = http.client.HTTPSConnection("api.pushover.net:443")
conn.request("POST", "/1/messages.json",
  urllib.parse.urlencode({
    "token": #API Token/Key
    "user": #User Key
    "title":"FIRE ALERT!!!",
    "message": "Evacuate Imidiately!",
    "priority":"1",
    "sound":"pushover"
  }), { "Content-type": "application/x-www-form-urlencoded" })
conn.getresponse()

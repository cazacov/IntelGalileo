/**
 * Created by Victor on 29.12.2014.
 */
var theThingsAPI = require('thethingsio-api');

module.exports = function() {
    //create Client
  var client = theThingsAPI.createClient();

  function sendAction(actionName) {
    console.log("Sending action: " + actionName);
    var jsonToSend = {
      "values": [
        {
          "key": "motion",
          "value": actionName,
          "units": "",
          "type": "temporal"
        }
      ]
    };

    var req1 = client.thingWrite(jsonToSend);
    req1.on('response', function (res) {
      console.log("Got response!")
    });
    req1.end();
  }

  function processKey(keyName)
  {
    if (keyName === "down")
    {
      sendAction("stop");
    }
    else if (keyName === "up")
    {
      sendAction("go");
    }
    else if (keyName === "left")
    {
      sendAction("left");
    }
    else if (keyName === "right")
    {
      sendAction("right");
    }
    else
    {
      // do nothing
    }
  }

  return {
    sendAction: sendAction,
    processKey: processKey
  };
}();
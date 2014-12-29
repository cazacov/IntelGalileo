/*jslint node:true, vars:true, bitwise:true, unparam:true */
/*jshint unused:true */
/*global */

var theThingsAPI = require('thethingsio-api');
var motorController = require("./motorController.js")
motorController.stop();

var ledController = require("./ledController.js")

//motorController.demo();

var motionKEY = 'motion';

//create Client
var client = theThingsAPI.createClient();
var lastAction = "@@@";

function readMotions()
{
    //read latest write
    var req1 = client.thingReadLatest(motionKEY);

    //event fired when the response arrives
    req1.on('response',function(res){
        if (res.statusCode == 200 && res.payload !== undefined)
        {
            var payload = JSON.parse(res.payload);
            var newAction = payload.data[0].value;
            console.log(newAction);
            if (newAction !== lastAction)
            {
                lastAction = newAction;
                motorController.doAction(newAction);
            }
        }
    });
    req1.end();
}

ledController.clear();
ledController.smile();

readMotions();
motorController.stop();

var loopCounter = 0;
setInterval(function() {
    console.log(loopCounter++);
    readMotions();
}, 200);

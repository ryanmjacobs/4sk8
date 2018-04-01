#!/usr/bin/env node

// webserver
const Koa = require("koa");
const bodyParser = require("koa-bodyparser");
const app = new Koa();
app.use(bodyParser());


// foursquare API call
const request = require('request');

request ({
    url: 'https://api.foursquare.com/v2/venues/VENUE_ID',
    method: 'GET',
    qs: {
	client_id: 'HODCT5S5JUALANRPIPQSM1JNF5IVWEADHOH1SP04M40OAHLD',
	client_secret: 'ZSIN13M2K2MUI3CDDLIRNKQQIWJDGC4Y0SV3Z4N5IMY2XM35',
	VENUE_ID: "Starbucks", // intended location; given by user
	v: 20180323
    }
}, function (err,res,body) {
    if(err) {
	console.error(err);
    } else {
	console.log(JSON.parse(body));
    }
});




app.use(async (ctx, next) => {
    console.log(ctx.method, ctx.url);
    await next();
});

app.use(async ctx => {
    const p = ctx.request.body;
    const req = ctx.request.method + ctx.url;

    console.log(p)
    console.log(p.lat, p.lon);

    ctx.body = {};
    ctx.body.example = "yup";
    ctx.body.goalLat = 123123.123123;

    if (p.lon == 4)
        ctx.body.goalLon = 7777;
    else
        ctx.body.goalLon = 0;
});

app.listen(4848, function() {
    console.log("listening http://0.0.0.0:4848");
});

#!/usr/bin/env node

// webserver
const Koa = require("koa");
const bodyParser = require("koa-bodyparser");
const app = new Koa();
app.use(bodyParser());


// foursquare API call
const request = require('request');

function get_venues(lat, lon, query) {
    return new Promise((resolve, reject) => {
        lat = lat || "34.0678";
        lon = lon || "-118.4507";

        request ({
            url: 'https://api.foursquare.com/v2/venues/explore',
            method: 'GET',
            qs: {
                client_id: 'HODCT5S5JUALANRPIPQSM1JNF5IVWEADHOH1SP04M40OAHLD',
                client_secret: 'ZSIN13M2K2MUI3CDDLIRNKQQIWJDGC4Y0SV3Z4N5IMY2XM35',
                ll: `${lat},${lon}`, // user location; given by skateboard or website
                radius: 2000, // radius of area around user location
                query: query || 'ramen', // unless provided the app looks for a ramen joint
                v: '20180323', // version number
                limit: 5
            }
        }, function (err,res,body) {
            if(err) {
                console.error(err);
                reject(err);
            } else {
                const result = JSON.parse(body);
              //console.log(result);
              //console.log(JSON.stringify(result.response.groups[0].items, null, 2));
                resolve(result.response.groups[0].items);
            }
        });
    });
}

app.use(async (ctx, next) => {
    console.log(ctx.method, ctx.url);
    await next();
});

app.use(async ctx => {
    const p = ctx.request.body;
    const req = ctx.request.method + ctx.url;

    console.log(p)
    console.log(p.lat, p.lon);

    const items = await get_venues(p.lat, p.lon, p.query);
    const venue = items[0].venue;

    if (ctx.request.method == "GET") {
        ctx.body = items.map(e => {
            return {
              name: e.venue.name,
              open: e.venue.hours ? e.venue.hours.isOpen : "unknown",
              lat: e.venue.location.lat,
              lon: e.venue.location.lng}
        });
    } else if (ctx.request.method == "POST") {
        ctx.body = "response";
    }
});

app.listen(4848, function() {
    console.log("listening http://0.0.0.0:4848");
});

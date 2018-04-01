#!/usr/bin/env node

// webserver
const Koa = require("koa");
const send = require("koa-send");
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

let plat=-1, plon=-1;
app.use(async (ctx, next) => {
    const p = ctx.request.body;
    console.log(ctx.request);
    const req = ctx.request.method + ctx.url;
    
    if (ctx.path.startsWith("/query/")) {
        p.query = p.query || ctx.path.split("/")[2];
        console.log(p);
    } else if (ctx.path == "/aquery") {
        ctx.body = {
            lat: plat,
            lon: plon
        };
        return;
    } else {
        console.log(ctx.path);
        if (ctx.path == "/")
            ctx.path = "/index.html";
        await send(ctx, "/static" + ctx.path);
        return;
    }

    console.log(p)
    console.log(p.lat, p.lon);

    const items = await get_venues(p.lat, p.lon, p.query);
    let randI = Math.floor(Math.random());
    
    const venue = items[randI].venue;

    ctx.body = items.map(e => {
        return {
          name: e.venue.name,
          open: e.venue.hours ? e.venue.hours.isOpen : "unknown",
          lat: e.venue.location.lat,
          lon: e.venue.location.lng}
    });

    
    ctx.body = ctx.body.filter(e => e.open === true);
    let len = ctx.body.length;
    randI = Math.floor(Math.random()*len);

    if(len == 0){
	ctx.body = "null";
    }
    else
	ctx.body = ctx.body[randI];
    plat = ctx.body.lat;
    plon = ctx.body.lon;
});

app.listen(4848, function() {
    console.log("listening http://0.0.0.0:4848");
});

#!/usr/bin/env node

// webserver
const Koa = require("koa");
const bodyParser = require("koa-bodyparser");
const app = new Koa();
app.use(bodyParser());

app.use(async (ctx, next) => {
    console.log(ctx.method, ctx.url);
    await next();
});

app.use(async ctx => {
    const p = ctx.request.body;
    const req = ctx.request.method + ctx.url;
    
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

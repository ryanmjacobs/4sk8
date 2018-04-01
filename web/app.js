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
    
    ctx.body = {
        hello: "world"
    };
});

app.listen(4848, function() {
    console.log("listening http://0.0.0.0:4848");
});

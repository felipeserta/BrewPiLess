const char data_bwf_js[] PROGMEM =
R"END(
function invoke(b){var c=new XMLHttpRequest();c.onreadystatechange=function(){if(c.readyState==4){if(c.status==200){b.success(c.responseText)}else{c.onerror(c.status)}}};c.ontimeout=function(){if(typeof b["timeout"]!="undefined")b.timeout();else c.onerror(-1)},c.onerror=function(a){if(typeof b["fail"]!="undefined")b.fail(a)};c.open(b.m,b.url,true);if(typeof b["data"]!="undefined"){c.setRequestHeader("Content-Type",(typeof b["mime"]!="undefined")?b["mime"]:"application/x-www-form-urlencoded");c.send(b.data)}else c.send()}var BWF={BrewProfile:"/brewing.json",sse:true,process:function(a){if(this.raw!=null){this.raw(a);return}eval("m={"+a+"}");for(var b in m){if(typeof this.handlers[b]!="undefined"){this.handlers[b](m[b])}}},on:function(a,b){this.handlers[a]=b},send:function(c,d){d=(typeof d=="undefined")?{}:d;var b=this;invoke({m:"POST",url:"/putline",mime:"application/x-www-form-urlencoded",data:"data="+encodeURI(c),success:function(){if(typeof d.success!=="undefined")d.success()},fail:function(a){if(typeof d.fail!=="undefined")d.fail(a);else b.error(a)}})},connect:function(){var b=this;var a=new EventSource("/getline");a.onmessage=function(e){b.process(e.data)};a.onerror=function(){setTimeout(function(){b.connnect()},3100)};setTimeout(function(){b.onopen()},1000)},init:function(c){var b=this;b.error=(typeof c.error=="undefined")?function(){}:c.error;b.handlers=(typeof c.handlers=="undefined")?{}:c.handlers;b.raw=(typeof c.raw=="undefined")?null:c.raw;b.onopen=(typeof c.onopen=="undefined")?function(){}:c.onopen;if(typeof EventSource==="undefined"){console.log("not support SSE");b.sse=false;var p=(typeof c.polling=="undefined")?5000:c.polling;setInterval(function(){invoke({m:"GET",url:"/getline_p",success:function(d){b.process(d)},fail:function(a){b.error(a)}})},p);return}b.connect()},save:function(a,b,c,d){invoke({m:"POST",url:"/fputs",data:"path="+a+"&content="+b,success:function(){c()},fail:function(e){d(e)}})},load:function(a,b,c){invoke({m:"GET",url:a,success:function(d){b(d)},fail:function(e){c(e)}})}};
)END";













































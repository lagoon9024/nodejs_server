const express= require('express');
const app = express();

const bodyParser = require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:true}));

app.use('/log', require('./logupdate/logupdate.js'));
app.use('/timeset', require('./timeset/timeset.js'));

module.exports=app;

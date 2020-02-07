const mysql = require('mysql');
const localmapper = require('mybatis-mapper');

const localconn = require('../../config/local_db.js');
const localcon = mysql.createConnection(localconn);


let format = {language: 'sql', indent: ' '};

var timetable={
    _time : '000000',
    amount : 0
}

const updateTable = function(req,res){
    localmapper.createMapper(['./mapper/timetable.xml'])
    let query = localmapper.getStatement('local_timetable', 'truncatetable', format);
    localcon.query(query, function(err,rows){
        if(err) throw err;
        console.log("truncated");
    })
    console.log(req.body);
    if(req){
        for(var i = 0 ; i<req.body.length; ++i){
            timetable._time= req.body[i].s_Time;
            timetable.amount= req.body[i].s_Amount;
            let query = localmapper.getStatement('local_timetable', 'updatetimetable', timetable, format);
            localcon.query(query, function(err, vars){
                if(err) throw err;
            })
        }
        console.log("UPDATE TIMETABLE :: "+ req.body.length+" DATA UPDATED");
        res.json("DEVICE 1 TIME TABlE :: " + req.body.length+" DATA UPDATED");
    }
}

module.exports = {
    updateTable : updateTable,
};

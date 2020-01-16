var express = require('express');
var models = require('../models');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/* POST Database */

router.post('/addMembers', function(req,res){
  var name = req.body.name;
  var id = req.body.id;
  var pw = req.body.pw;
  var email = req.body.email;

  models.users.create({id, pw, name, email})
  .then(result =>{
    res.json(result);
  })
  .catch(err=>{
    console.error(err);
  })

  //res.send("insert Success!");
});


router.post('/login', function(req,res){
  var loginid = req.body.id;
  var loginpw = req.body.pw;
  models.users.findOne({where:{id: loginid ,pw: loginpw} })
  .then((result)=>{
    if(result)
    res.send('true');
    else
    res.send('false');
  })
  .catch(err=>{    
    console.err(err);
  })
});



module.exports = router;

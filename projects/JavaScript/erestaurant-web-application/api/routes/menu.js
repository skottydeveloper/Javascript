var express = require('express');
var router = express.Router();
const ObjectID = require('mongodb').ObjectID;

router.get('/filter/:type/:value', (req, res, next) => {
    const { type, value } = req.params; 
    req.menuCollection.find({ [type]: value })
      .toArray()
      .then(results => res.json(results))
      .catch(err => res.send(err));
  });

router.get('/filters', (req, res, next) => {
    const fields = ['category'];
    const dbRequests = fields.map(field => 
      req.menuCollection
        .distinct(field)
        .then(data => ({ field, data: data.sort() }))
      );
    
    Promise.all(dbRequests)
      .then(results => {
        const reducedResults = results.reduce((acc, {field, data}) => ({ ...acc, [field]: data }), {})
        res.json(reducedResults);
      })
      .catch(err => res.send(err));
  });

router.get('/menu', (req, res, next) => {
    req.menuCollection.find({})
      .toArray()
      .then(results => res.json(results))
      .catch(err => res.send(err));
  });

router.get('/menu/:id', (req, res, next) => {
    const _id = ObjectID(req.params.id);
    req.menuCollection.findOne({ _id })
      .then(results => res.json(results))
      .catch(err => res.send(err));
  });
  module.exports = router;
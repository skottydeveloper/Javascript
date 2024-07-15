var express = require('express');
var router = express.Router();
const ObjectID = require('mongodb').ObjectID;

router.get('/reservations', (req, res, next) => {
  req.reservationsCollection.find({})
    .toArray()
    .then(results => res.json(results))
    .catch(error => res.send(error));
});

router.post('/reservations', (req, res, next) => {
  const { reservationDate, name, time } = req.body;
  if (!reservationDate || !name || !time) {
    return res.status(400).json({
      message: 'reservation Date, Name and Time are required',
    });
  }

  const payload = { reservationDate, name, time };
  req.reservationsCollection.insertOne(payload)
    .then(result => res.json(result.ops[0]))
    .catch(error => res.send(error));
});

router.delete('/reservations/:id', (req, res, next) => {
  const { id } = req.params;
  const _id = ObjectID(id);
  req.reservationsCollection.deleteOne({ _id })
    .then(result => res.json(result))
    .catch(error => res.send(error));
});
router.get('/filters', (req, res, next) => {
  const fields = ['category'];
  const dbRequests = fields.map(field => 
    req.reservationsCollection
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

router.get('/filter/:type/:value', (req, res, next) => {
  const { type, value } = req.params; 
  req.reservationsCollection.find({ [type]: value })
    .toArray()
    .then(results => res.json(results))
    .catch(err => res.send(err));
});

module.exports = router;
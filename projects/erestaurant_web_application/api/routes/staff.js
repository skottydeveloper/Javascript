var express = require('express');
var router = express.Router();
const ObjectID = require('mongodb').ObjectID;

router.get('/filters', (req, res, next) => {
  const fields = ['name', 'role'];
  const dbRequests = fields.map(field =>
    req.staffCollection
      .distinct(field)
      .then(data => ({ field, data: data.sort() } ))
    );

  Promise.all(dbRequests)
    .then(results => {
      const reducedResults = results.reduce((acc, { field, data }) => (
        { ...acc, [field]: data }
      ), {});
      res.json(reducedResults);
    })
    .catch(err => res.send(err));
});

router.get('/filter/:type/:value', (req, res, next) => {
  const { type, value } = req.params; 
  req.staffCollection.find({ [type]: value })
    .toArray()
    .then(results => res.json(results))
    .catch(err => res.send(err));
});

router.get('/get', (req, res, next) => {
  req.staffCollection.find({})
  .toArray()
  .then(results => res.json(results))
  .catch(err => res.send(err));
});

router.get('/:id', (req, res, next) => {
  const _id = ObjectID(req.params.id);
  req.staffCollection.findOne({ _id })
  .then(results => res.json(results))
  .catch(err => res.send(err));
});

router.post('/post', (req, res, next) => {
  const { name, role, email, phone } = req.body;
  if (!name || !role || !email || !phone) {
    return res.status(400).json({
      message: 'lol wrong',
    });
  }

  const payload = { name, role, email, phone };
  req.staffCollection.insertOne(payload)
    .then(result => res.json(result.ops[0]))
    .catch(error => res.send(error));
});

module.exports = router;

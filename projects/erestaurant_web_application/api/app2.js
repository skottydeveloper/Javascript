var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

const config = require('./config');
const MongoClient = require('mongodb').MongoClient;
const cors = require('cors');

var staffRouter = require('./routes/staff');
var reservationsRouter = require('./routes/reservations');
var menuRouter = require('./routes/menu');

var app = express();

MongoClient.connect(`mongodb://${config.dbHost}`, { useNewUrlParser: true, useUnifiedTopology: true })
  .then(client => {
    const db = client.db(config.dbName);
    const reservationsCollection = db.collection(config.reservationsCollection);
    const menuCollection = db.collection(config.menuCollection);
    const staffCollection = db.collection(config.staffCollection);  
    app.locals[config.menuCollection] = menuCollection;
    app.locals[config.staffCollection] = staffCollection;
    app.locals[config.reservationsCollection] = reservationsCollection;
  })
  .catch(error => {
    console.log(error);
  });

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors());

app.use((req, res, next) => {
  const staffCollection = req.app.locals[config.staffCollection];
  req.staffCollection = staffCollection;
  const reservationsCollection = req.app.locals[config.reservationsCollection];
  req.reservationsCollection = reservationsCollection;
  const menuCollection = req.app.locals[config.menuCollection];
  req.menuCollection = menuCollection;
  next();
});

app.use('/menu', menuRouter);
app.use('/reservations', reservationsRouter);
app.use('/staff', staffRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;

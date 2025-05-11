const config = require('./config');
const MongoClient = require('mongodb').MongoClient;
const parser = require('csv-parse/lib/sync');
const fs = require('fs');
const path = require('path');

let mongoClient; 
MongoClient.connect(`mongodb://${config.dbHost}`, { useNewUrlParser: true })

  .then(client => {
    mongoClient = client;
    const db = client.db(config.dbName);
    const reservationsCollection = db.collection(config.reservationsCollection);
    const sourceData = fs.readFileSync(path.join(__dirname, config.sourceReservationFile), 'utf8');
    const documents = parser(sourceData, { columns: true, skip_empty_lines: true });
    reservationsCollection.insertMany(documents, (err) => {
      if (err) {
        throw err;
      }

      console.log(`Documents imported successfully to: ${config.reservationsCollection}`);
    })
    return client;
  })
  .then(client => {
    mongoClient = client;
    const db = client.db(config.dbName);
    const menuCollection = db.collection(config.menuCollection);
    const sourceData = fs.readFileSync(path.join(__dirname, config.sourceMenuFile), 'utf8');
    const documents = parser(sourceData, { columns: true, skip_empty_lines: true });
    menuCollection.insertMany(documents, (err) => {
      if (err) {
        throw err;
      }

      console.log(`Documents imported successfully to: ${config.menuCollection}`);
    })
    return client;
  })
  .then(client => {
    mongoClient = client;
    const db = client.db(config.dbName);
    const staffCollection = db.collection(config.staffCollection);
    const sourceData = fs.readFileSync(path.join(__dirname, config.sourceStaffFile), 'utf8');
    const documents = parser(sourceData, { columns: true, skip_empty_lines: true });
    staffCollection.insertMany(documents, (err) => {
      if (err) {
        throw err;
      }

      console.log(`Documents imported successfully to: ${config.staffCollection}`);
      mongoClient.close();
    })
  })
  .catch(error => {
    console.log('There was an error seeding the database: ', error);
  });
/*
  .then(client => {
    mongoClient = client;
    const db = client.db(config.dbName);
    const menuCollection = db.collection(config.menuCollection);
    return menuCollection;
  })
  .then(menuCollection => {
    const sourceData = fs.readFileSync(path.join(__dirname, config.sourceMenuFile), 'utf8');
    const documents = parser(sourceData, { columns: true, skip_empty_lines: true });
    menuCollection.insertMany(documents, (err) => {
      if (err) {
        throw err;
      }

      console.log(`Documents imported successfully to: ${config.menuCollection}`);
      mongoClient.close();
    })
  })
  .catch(error => {
    console.log('There was an error seeding the database: ', error);
  })


  .then(client => {
    mongoClient = client;
    const db = client.db(config.dbName);
    const staffCollection = db.collection(config.staffCollection);
    return staffCollection;
  })
  .then(staffCollection => {
    const sourceData = fs.readFileSync(path.join(__dirname, config.sourceStaffFile), 'utf8');
    const documents = parser(sourceData, { columns: true, skip_empty_lines: true });
    staffCollection.insertMany(documents, (err) => {
      if (err) {
        throw err;
      }

      console.log(`Documents imported successfully to: ${config.staffCollection}`);
      mongoClient.close();
    })
  })
  .catch(error => {
    console.log('There was an error seeding the database: ', error);
  })*/
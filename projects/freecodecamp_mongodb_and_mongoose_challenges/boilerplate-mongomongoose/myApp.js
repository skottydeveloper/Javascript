require('dotenv').config();

/* 1. Install & Setup Mongoose */
const mongoose = require('mongoose');
mongoose.connect(process.env.MONGO_URI, { useNewUrlParser: true });

/* 2. Create a Model */
const Schema = mongoose.Schema;

const personSchema = new Schema({
  name: { type: String, required: true },
  age: Number,
  favoriteFoods: [String]
});

/* 3. Create and Save a Person */
const Person = mongoose.model('Person', personSchema);

const createAndSavePerson = function(done) {
  const person = new Person({name: "Steve", age: 57, favoriteFoods: ["meat", "yogurt", "vegetables"]});

  person.save(function(err, data) {
    if (err) return console.error(err);
    done(null, data)
  });
};

/* 4. Create Many Records with 'model.create()' */
const arrayOfPeople = [
  {name: "Andreas", age: 21, favoriteFoods: ["Spaghetti Bolognese"]},
  {name: "Fernando", age: 41, favoriteFoods: ["Pizza"]},
  {name: "Lewis", age: 38, favoriteFoods: ["Stir-fried Vegetable Dish"]}
];

const createManyPeople = function(arrayOfPeople, done) {
  Person.create(arrayOfPeople, function(err, people) {
    if (err) return console.log(err);
    done(null, people);
  });
};

/* 5. 'Use model.find()' to Search Your Database */
const findPeopleByName = function(personName, done) {
  Person.find({name: personName}, function(err, personFound) {
    if (err) return console.log(err);
    done(null, personFound);
  });
};

const findOneByFood = (food, done) => {
  done(null /*, data*/);
};

const findPersonById = (personId, done) => {
  done(null /*, data*/);
};

const findEditThenSave = (personId, done) => {
  const foodToAdd = "hamburger";

  done(null /*, data*/);
};

const findAndUpdate = (personName, done) => {
  const ageToSet = 20;

  done(null /*, data*/);
};

const removeById = (personId, done) => {
  done(null /*, data*/);
};

const removeManyPeople = (done) => {
  const nameToRemove = "Mary";

  done(null /*, data*/);
};

const queryChain = (done) => {
  const foodToSearch = "burrito";

  done(null /*, data*/);
};

/** **Well Done !!**
/* You completed these challenges, let's go celebrate !
 */

//----- **DO NOT EDIT BELOW THIS LINE** ----------------------------------

exports.PersonModel = Person;
exports.createAndSavePerson = createAndSavePerson;
exports.findPeopleByName = findPeopleByName;
exports.findOneByFood = findOneByFood;
exports.findPersonById = findPersonById;
exports.findEditThenSave = findEditThenSave;
exports.findAndUpdate = findAndUpdate;
exports.createManyPeople = createManyPeople;
exports.removeById = removeById;
exports.removeManyPeople = removeManyPeople;
exports.queryChain = queryChain;

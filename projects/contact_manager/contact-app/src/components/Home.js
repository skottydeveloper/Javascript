import React, {useState, useEffect } from 'react';
import { useMatch } from 'react-router-dom';
import Contacts from './Contacts';
import { Routes, Route } from 'react-router';

const Home = () => {
    const [contacts, setContacts] = useState([]);
    const [displayContacts, setDisplayContacts] = useState(0);

    useEffect(() => {
        fetch('https://jsonplaceholder.typicode.com/users')
            .then(res => res.json())
            .then(data => {
                setContacts(data)
                setDisplayContacts(data)
            })
    }, [])

    let { path } = useMatch();

    // Search bar functionality
    const handleSearch = (event) => {
        const searchText = event.target.value;
        const matchedContacts = contacts.filter(contact => contact.name.toLowerCase().includes(searchText.toLowerCase()));
        setDisplayContacts(matchedContacts);
    }

    return (
        <>
            {
                      <div id="page-content-wrapper">
                          <nav className="navbar navbar-expand-lg navbar-light bg-transparent py-4 px-4 d-flex justify-content-between">
                              <div className="d-flex align-items-center">
                                  <h3 className="m-0 text-uppercase home-title">Contacts Viewer</h3>
                              </div>
                              <div className="col-12 mt-3 mt-md-0 col-md-7">
                                  <input onChange={handleSearch} class="form-control me-2" type="search" placeholder="Search..." aria-label="Search..." />
                              </div>
                          </nav>

                          <div className="container-fluid px-4">
                              <Routes>
                                  <Route exact path={path}>
                                      <Contacts contacts={displayContacts}></Contacts>
                                  </Route>
                              </Routes>
                          </div>
                      </div>
            }
        </>
    );
}; 

export default Home;
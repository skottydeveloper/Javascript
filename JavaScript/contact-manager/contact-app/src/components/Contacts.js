import React, { useState, useEffect } from 'react';
import Profile from './Profile';
import error from '../images/question-mark.png';

const Contacts = ({ contacts }) => {
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    if (contacts) {
      setIsLoading(false);
    }
  }, [contacts]);

  if (isLoading) {
    return <div>Loading...</div>;
  }

  if (!Array.isArray(contacts)) {
    return null;
  }

  return (
    <div>
      {contacts.length ? (
        <div className="text-start mt-0 mt-md-4">
          <table className="table table-hover">
            <thead>
              <tr>
                <th scope="col">Name</th>
                <th className="d-none d-lg-table-cell" scope="col">Phone</th>
                <th className="d-none d-lg-table-cell" scope="col">Email</th>
              </tr>
            </thead>
            <tbody>
              {contacts.map((contact) => (
                <Profile key={contact.id} contact={contact}></Profile>
              ))}
            </tbody>
          </table>
        </div>
      ) : (
        <div className="mt-4">
          <h1 className="fw-bold">No Contacts Found</h1>
          <p>No results retrieved.</p>
          <img
            className="img-fluid col-9 col-md-6 col-lg-3 mx-auto"
            src={error}
            alt=""
          />
        </div>
      )}
    </div>
  );
};

export default Contacts;
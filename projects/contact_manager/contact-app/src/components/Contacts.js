import React from 'react';
import Profile from './Profile';
import error from '../images/question-mark.png';

const Contacts = ({ contacts }) => {
    return (
        <div>
            {
                contacts.length
                    ?
                    <div className="text-start mt-0 mt-md-4">
                        <table class="table table-hover">
                            <thead>
                                <tr>
                                    <th scope="col">Name</th>
                                    <th className="d-none d-lg-table-cell" scope="col">Phone</th>
                                    <th className="d-none d-lg-table-cell" scope="col">Email</th>
                                </tr>
                            </thead>
                            <tbody>
                                {
                                    contacts.map(user => <Profile
                                        key={user.id}
                                        user={user}
                                    ></Profile>)
                                }
                            </tbody>
                        </table>

                    </div>
                    :
                    <div className="mt-4">
                        <h1 className="fw-bold">No Contacts Found</h1>
                        <p>No results retrieved.</p>
                        <img className="img-fluid col-9 col-md-6 col-lg-3 mx-auto" src={error} alt="" />
                    </div>
            }
        </div>
    );
};

export default Contacts;
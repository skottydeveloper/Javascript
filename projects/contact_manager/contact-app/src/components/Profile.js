import React, { useState } from 'react';
import { Modal, Button } from 'react-bootstrap';
import user from "../images/user.png";

const Profile = ({ contact }) => {
  const [show, setShow] = useState(false);

  if (!contact) return null;
    
  const { id, name, username, email, address, phone, website, company } = contact;
  
  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  return (
    <>
      <tr className="mb-4" onClick={handleShow}>
        <td className="py-3">
          <img className="ui avatar image" src={user} alt="user" />
          <span>
            {name}
          </span>
        </td>
        <td className="d-none d-lg-table-cell py-3">{phone}</td>
        <td className="d-none d-lg-table-cell py-3">{email}</td>
      </tr>

      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>{name}</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <ul>
            <li><span className="fw-bold">ID</span> : {id}</li>
            <li><span className="fw-bold">Username</span> : {username}</li>
            <li><span className="fw-bold">Email</span> : {email}</li>
            <li><span className="fw-bold">Phone</span> : {phone}</li>
            <li><span className="fw-bold">Website</span> : {website}</li>
            <li><span className="fw-bold">Address</span> :
              {address.street + ", " + address.suite + ", " + address.city + ", " + address.zipcode}
            </li>
            <li><span className="fw-bold">Company</span> : {company.name}</li>
          </ul>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>
    </>
  );
};

export default Profile;
import React, { useEffect, useState } from 'react';
import socket from '../socket';
import Constants from '../constents';
import { useRouter } from 'next/router';
import styles from '../styles/login.module.css'

const Signup = () => {
  const router = useRouter();
  const [userName, setUserName] = useState('');
  const [password, setPassword] = useState('');
  const [email, setEmail] = useState('');
  const [address, setAddress] = useState('');
  const [phoneNumber, setPhoneNumber] = useState('');
  const [birthDate, setBirthDate] = useState('');


  const [passwordError, setPasswordError] = useState('');
  const [emailError, setEmailError] = useState('');
  const [birthDateError, setBirthDateError] = useState('');
  const [phoneNumberError, setPhoneNumberError] = useState('')
  const [addressError, setAddressError] = useState('';)

  // Constants for validations
  const MIN_PASSWORD_SIZE = 8;

  // Function to check password validity
  function checkPassword() {
    // Check if password is at least 8 characters long
    if (password.length < MIN_PASSWORD_SIZE) {
      setPasswordError("Password must be at least 8 characters long");
      return false
    }
    // Check if password has a capital letter
    if (!/[A-Z]/.test(password)) {
      setAddressError("Password must contain a capitel letter");
      return false
    }
    // Check if password has a lowercase letter
    if (!/[a-z]/.test(password)) {
      setAddressError("Password must contain a lower case letter");
      return false;
    }
    // Check if password has a number
    if (!/[0-9]/.test(password)) {
      setAddressError("Password must contain a digit");
      return false;
    }
    return true;
  }

  // Function to check email validity
  function checkEmail() {
    const pattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    if (!pattern.test(email)) {
      setEmailError("Email is not at format");
      return false;
    }
    return true;
  }

  // Function to check address validity
  function checkAddress() {
    const pattern = /^[a-zA-Z]+,\s[0-9]+,\s[a-zA-Z]+$/;
    if (!pattern.test(address)) {
      setAddressError("Address is not at format");
      return false;
    }
    return true;
  }

  // Function to check phone number validity
  function checkPhone() {
    const pattern = /^0[0-9]{2,3}-[0-9]+$/;
    if (!pattern.test(phoneNumber)) {
      setPhoneNumberError("Phone number is not at format");
      return false;
    };
    return true;
  }

  // Function to check birth date validity
  function checkBirth() {
    const pattern = /^(0[1-9]|[12][0-9]|3[01])[\/\.](0[1-9]|1[012])[\/\.]\d{4}$/;
    if (!pattern.test(birth)) {
      setBirthDateError("birth date not at format");
      return false;
    }
    return true;
  }

  useEffect(() => {
    checkEmail();
    checkPassword();
    checkAddress();
    checkPhone();
    checkBirth();
  });


  const handleSignup = (e) => {
    e.preventDefault(); // Prevent the form from refreshing the page
    const allValid = checkPassword(password) && checkEmail(email) &&
      checkAddress(address) && checkPhone(phoneNumber) &&
      checkBirth(birthDate);

    if (!allValid) {
      // Handle errors here
      setPasswordError("Invalid password format");
      return; // Stop the signup process if validation fails
    }

    // Emit the signup event to the server with username and password
    socket.emit('signup', JSON.stringify({
      username: userName,
      password,
      email,
      address,
      phoneNumber,
      birthDate
    }));


    return (
      <div className={styles.mainContainer}>
        <div className={styles.titleContainer}>
          <div>Signup</div>
        </div>
        <br />

        <div className={styles.inputContainer}>
          <input
            value={userName}
            placeholder="Enter your user name here"
            onChange={(ev) => setUserName(ev.target.value)}
            className={styles.inputBox}
          />
        </div>
        <br />

        <div className={styles.inputContainer}>
          <input
            value={password}
            placeholder="Enter your password here"
            onChange={(ev) => setPassword(ev.target.value)}
            className={styles.inputBox}
          />
          <label className={styles.errorLabel}>{passwordError}</label>
        </div>
        <br />

        <div className={styles.inputContainer}>
          <input
            value={email}
            placeholder="Enter your email here"
            onChange={(ev) => setEmail(ev.target.value)}
            className={styles.inputBox}
          />
          <label className={styles.errorLabel}>{emailError}</label>
        </div>
        <br />
        <div className={styles.inputContainer}>
          <input className={styles.inputButton} type="button" value="Login" onClick={handleLogin} />
        </div>
      </div>
    );
  };

  export default Login;
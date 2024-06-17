import TextInput from "./UserNameInput";
import styles from "./RegisterForm.module.css";
import { useNavigate } from "react-router-dom";
import { useState, useEffect } from "react";
import Constants from "../Constants";
import { socket } from "../socket";

const RegisterForm = () => {
  const navigate = useNavigate();

  const [userName, setUserName] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const [address, setAddress] = useState("");
  const [phoneNumber, setPhoneNumber] = useState("");
  const [birthDate, setBirthDate] = useState("");

  function handleFormSubmit(event) {
    event.preventDefault(); // Prevent the default form submission behavior
    socket.emit("signup", {
      [Constants.FIELDS.USER_NAME]: userName,
      [Constants.FIELDS.PASSWORD]: password,
      [Constants.FIELDS.EMAIL]: email,
      [Constants.FIELDS.ADDRESS]: address,
      [Constants.FIELDS.PHONE_NUMBER]: phoneNumber,
      [Constants.FIELDS.BIRTH_DATE]: birthDate
    });
  }

  function navigateToLogin() {
    navigate("/login")
  }

  useEffect(() => {
    // Event listener for 'SignUpResponse'
    socket.on('SignUpResponse', (response) => {
      if (response.status === Constants.WORK_STATUS) {
        navigate("/menu")
      } else {
        alert("somthing went wrong")
      }
    });

    // Cleanup: remove event listener when component unmounts
    return () => {
      socket.off('SignUpResponse');
    };
  }, []); // empty dependency array ensures the effect runs only once when component mounts

  return (
    <form className={styles.registerForm} onSubmit={handleFormSubmit}>
      <div className={styles.register}>Register</div>
      <div className={styles.mdipassword} />
      <div className={styles.frameParent}>
        <div className={styles.usernameInputParent}>
          <TextInput
            placeHolder="User name"
            icon="/wpfname.svg"
            setter={setUserName}
          />

          <TextInput
            placeHolder="Password"
            icon="/email-icon.svg"
            type="password"
            pattern="^(?=.*[A-Z])(?=.*[a-z])(?=.*\d).{8,}$"
            title="Password should be at least 8 digits and contain a capitel and smaal letter"
            setter={setPassword}
          />

          <TextInput
            placeHolder="Email"
            icon="/icbaselineemail.svg"
            type="email"
            setter={setEmail}
          />

          <TextInput
            placeHolder="Address"
            icon="/entypoaddress.svg"
            pattern="^[a-zA-Z]+,\s[0-9]+,\s[a-zA-Z]+$"
            title="The address should be like this: city, number, street"
            setter={setAddress}
          />

          <TextInput
            placeHolder="Phone number"
            icon="/phphonefill.svg"
            pattern="^0[0-9]{2,3}-[0-9]+$"
            title="ID must start with a '0' followed by 2 or 3 digits, a hyphen, and then more digits."
            setter={setPhoneNumber}
          />

          <TextInput
            placeHolder="Birth date"
            icon="/phphonefill.svg"
            type="date"
            title="ID must start with a '0' followed by 2 or 3 digits, a hyphen, and then more digits."
            setter={setBirthDate}
          />
        </div>
        <div className={styles.frameWrapper2}>
          <div className={styles.frameGroup}>
            <div className={styles.submitButtonWrapper}>
              <button type="submit" className={styles.submitButton}>
                Submit
              </button>
            </div>
            <div className={styles.alreadyAUserContainer}>
              <span>{`already a user? `}</span>
              <span className={styles.logIn} onClick={navigateToLogin}> {`log in `}</span>
            </div>
          </div>
        </div>
      </div>
    </form>
  );
};

export default RegisterForm;

import styles from "./Login.module.css";
import TextInput from "../components/UserNameInput";
import { useState, useEffect } from "react";
import { socket } from "../socket";
import { useNavigate } from "react-router-dom";
import Constents from '../Constants'

const Login = () => {
  const navigate = useNavigate();
  const [userName, setUserName] = useState('');
  const [password, setPassword] = useState('');

  function handleFormSubmit(event) {
    event.preventDefault(); // Prevent the default form submission behavior
    socket.emit("login", {
      [Constants.FIELDS.USER_NAME]: userName,
      [Constants.FIELDS.PASSWORD]: password,
    });
  }

  function navigateToRegister() {
    navigate("/")
  }

  useEffect(() => {
    // Event listener for 'SignUpResponse'
    socket.on('LoginResponse', (response) => {
      if (response.status === Constants.WORK_STATUS) {
        alert('worked');
        navigate("/menu")
      } else {
        alert("somthing went wrong")
      }
    });

    // Cleanup: remove event listener when component unmounts
    return () => {
      socket.off('LoginResponse');
    };
  }, []); // empty dependency array ensures the effect runs only once when component mounts
  
  return (
    <div className={styles.login}>
      <div className={styles.textInput}>
        <div className={styles.register}>Login</div>
        <div className={styles.textInputInner}>
          <form className={styles.formParent}>
            <div className={styles.form}>
              <TextInput
                placeHolder={"User name"}
                icon={"/wpfname.svg"}
                setter={setUserName}
              />
              <TextInput
                placeHolder={"Password"}
                icon={"/email-icon.svg"}
                setter={setPassword}
              />
            </div>
            <div className={styles.frameWrapper}>
              <div className={styles.frameParent}>
                <div className={styles.submitButtonWrapper}>
                  <button className={styles.submitButton}>
                    <div className={styles.submit}>Submit</div>
                  </button>
                </div>
                <div className={styles.alreadyAUserContainer}>
                  <span className={styles.notAUser}>{`Not a user?  `}</span>
                  <span className={styles.register1} onClick={navigateToRegister} >Register</span>
                  <span className={styles.span}>{` `}</span>
                </div>
              </div>
            </div>
          </form>
        </div>
      </div>
      <img className={styles.logo1Icon} alt="" src="/logo-1.svg" />
      <div className={styles.createdByYoelWeisbergAndNWrapper}>
        <div className={styles.createdByYoel}>
          Created by Yoel weisberg and neta orevi
        </div>
      </div>
    </div>
  );
};

export default Login;

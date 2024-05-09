import TextInput1 from "../components/TextInput1";
import styles from "./Register.module.css";

const Register = () => {
  return (
    <div className={styles.register}>
      <main className={styles.userInput}>
        <TextInput1 />
      </main>
      <img className={styles.logo1Icon} alt="" src="/logo-1.svg" />
      <div className={styles.createdByYoel}>
        Created by Yoel weisberg and neta orevi
      </div>
    </div>
  );
};

export default Register;

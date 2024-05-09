import RegisterForm from "../components/RegisterForm";
import styles from "./Register.module.css";

const Register = () => {
  return (
    <div className={styles.register}>
      <img className={styles.logo1Icon} alt="" src="/logo-1.svg" />
      <main className={styles.registerFormWrapper}>
        <RegisterForm />
      </main>
      <div className={styles.createdByYoel}>
        Created by Yoel weisberg and neta orevi
      </div>
    </div>
  );
};

export default Register;

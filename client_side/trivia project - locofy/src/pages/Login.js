import TextInput from "../components/TextInput";
import styles from "./Login.module.css";

const Login = () => {
  return (
    <div className={styles.login}>
      <TextInput />
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

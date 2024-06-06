import styles from "./ActionSectionNotAdmin.module.css";

const ActionSectionNotAdmin = () => {
  return (
    <div className={styles.actionSectionNotAdmin}>
      <div className={styles.askTheAdmin}>Ask the admin to start the game</div>
    </div>
  );
};

export default ActionSectionNotAdmin;

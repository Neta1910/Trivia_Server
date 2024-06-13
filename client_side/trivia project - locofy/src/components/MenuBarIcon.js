import styles from "./MenuBarIcon.module.css";

const MenuBarIcon = ({ menuBar }) => {
  return (
    <img className={styles.menuBarIcon} loading="lazy" alt="" src={menuBar} />
  );
};

export default MenuBarIcon;

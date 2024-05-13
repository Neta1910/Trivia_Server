import styles from './PlayerInHigh.module.css'

const PlayerInHigh = ({place, userName, score}) => {
    return (
        <div className={styles.player}>
        <div className={styles.frameParent}>
          <div className={styles.circleShapeParent}>
            <div className={styles.circleShape} />
            <div className={styles.separator}>{place}</div>
          </div>
          <div className={styles.userName}>{userName}</div>
        </div>
        <div className={styles.scoreWrapper}>
          <div className={styles.score}>{score}</div>
        </div>
      </div>
    )
}

export default PlayerInHigh
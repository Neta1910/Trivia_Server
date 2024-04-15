import React from 'react';
import styles from './RoomCard.module.css';
import { FaUsers, FaRegQuestionCircle, FaClock, FaToggleOn, FaToggleOff } from 'react-icons/fa';
import styles from '../styles/RoomCard.module.css';

const RoomCard = ({ roomName, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive }) => {
    return (
        <div className={styles.card}>
            <div className={styles.header}>
                <h2>{roomName}</h2>
                <div className={styles.status}>
                    {isActive ? <FaToggleOn className={styles.activeIcon} /> : <FaToggleOff className={styles.inactiveIcon} />}
                    {isActive ? 'Active' : 'Inactive'}
                </div>
            </div>
            <div className={styles.info}>
                <div className={styles.infoItem}>
                    <FaUsers />
                    <span>{maxPlayers} players</span>
                </div>
                <div className={styles.infoItem}>
                    <FaRegQuestionCircle />
                    <span>{numOfQuestionsInGame} questions</span>
                </div>
                <div className={styles.infoItem}>
                    <FaClock />
                    <span>{timePerQuestion} sec/question</span>
                </div>
            </div>
        </div>
    );
};

export default RoomCard;

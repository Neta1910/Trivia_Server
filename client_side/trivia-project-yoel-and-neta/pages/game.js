import { useEffect, useState } from "react"
import { useSocket } from "../componenets/socketContext";

const GameScreen = () => {
    const socket = useSocket();
    const [leftQuestions, setLeftQuestions ] = useState(0);
    const [rightAnsowers, setRightAnsowers] = useState(0);
    const [currentQuestion, setCurrentQuestion] = useState({})

    const getNextQuestion = () => {
        socket.emit("")
    }
    useEffect({

    });
}

import { useEffect, useState } from 'react';
import { socket } from '../socket';
import Constants from '../Constants';
import { useNavigate } from 'react-router-dom';
function Logout() {
    const [logginOut, setlogginOut] = useState(true);
    const navigate = useNavigate();
    useEffect(() => {
        socket.emit('logout');
        socket.on('logoutResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
                setlogginOut(false);
                navigate('/login')
            } else {
                alert('error while reiving from server, try again later');
            }
        });
    }, []);

    if(logginOut) return <p>Logging you out...</p>

    return (
        <p>Good bye, was nice to meet you</p>
    );
}

export default Logout;
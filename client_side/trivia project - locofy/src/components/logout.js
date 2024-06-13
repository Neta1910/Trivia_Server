import { useEffect, useState } from 'react';
import { socket } from '../socket';
import Constants from '../Constants';
function Logout() {
    const [logginOut, setlogginOut] = useState(true);
    useEffect(() => {
        socket.emit('logout');
        socket.on('logoutResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
                setlogginOut(false);
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
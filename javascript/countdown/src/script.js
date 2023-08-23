// Get the current date and time
const now = new Date();

// Set the target date and time for June 28, 2023, at 10 AM Finnish time
const targetTime = new Date("2023-06-28T10:00:00+03:00");

// Calculate the time difference in milliseconds
let timeDiff = targetTime - now;

// Update the countdown every second
const countdownInterval = setInterval(updateCountdown, 1000);

// Update the countdown text based on the current time
function updateCountdown() {
  const countdownElement = document.getElementById("countdown");
  const currentTime = new Date();
  timeDiff = targetTime - currentTime;

  if (timeDiff > 0) {
    const hours = Math.floor(timeDiff / (1000 * 60 * 60));
    const minutes = Math.floor((timeDiff % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((timeDiff % (1000 * 60)) / 1000);

    countdownElement.textContent = hours + "h " + minutes + "m " + seconds + "s";
  } else if (currentTime.getHours() === 10 && currentTime.getMinutes() < 30) {
    countdownElement.textContent = "Now";
  } else {
    countdownElement.textContent = "Done";
    clearInterval(countdownInterval);
  }
}
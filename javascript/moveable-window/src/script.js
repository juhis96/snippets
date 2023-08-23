// Get the button and window elements
const openButton = document.getElementById('open-button');
const windowElement = document.getElementById('window');

// Function to handle the open button click event
function openButtonClicked() {
  windowElement.style.display = 'block';
}

// Add event listener to the open button
openButton.addEventListener('click', openButtonClicked);

// Rest of the JavaScript code (dragging and close button functionality) remains the same
// Track the initial mouse position and window position
let initialMouseX = 0;
let initialMouseY = 0;
let initialWindowX = 0;
let initialWindowY = 0;

// Function to handle the start of dragging
function startDragging(event) {
  initialMouseX = event.clientX;
  initialMouseY = event.clientY;
  initialWindowX = windowElement.offsetLeft;
  initialWindowY = windowElement.offsetTop;

  // Add event listeners for the dragging actions
  document.addEventListener('mousemove', dragWindow);
  document.addEventListener('mouseup', stopDragging);
}

// Function to handle the dragging action
function dragWindow(event) {
  const dx = event.clientX - initialMouseX;
  const dy = event.clientY - initialMouseY;
  windowElement.style.left = initialWindowX + dx + 'px';
  windowElement.style.top = initialWindowY + dy + 'px';
}

// Function to handle the end of dragging
function stopDragging() {
  document.removeEventListener('mousemove', dragWindow);
  document.removeEventListener('mouseup', stopDragging);
}

// Add event listeners to the title bar for dragging
const titleBar = document.querySelector('.title-bar');
titleBar.addEventListener('mousedown', startDragging);

// Function to handle the close button
function closeButtonClicked() {
  windowElement.style.display = 'none';
}

// Add event listener to the close button
const closeButton = document.querySelector('.close-button');
closeButton.addEventListener('click', closeButtonClicked);
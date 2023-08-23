const sections = document.querySelectorAll('.section');

window.addEventListener('wheel', handleScroll);

function handleScroll(event) {
  event.preventDefault();
  const delta = event.deltaY || event.detail || (-event.wheelDelta);

  let activeSection = null;

  sections.forEach((section, index) => {
    const rect = section.getBoundingClientRect();
    if (rect.top >= 0 && rect.bottom <= window.innerHeight) {
      activeSection = index;
    }
  });

  if (delta > 0 && activeSection < sections.length - 1) {
    sections[activeSection + 1].scrollIntoView({ behavior: 'smooth' });
  } else if (delta < 0 && activeSection > 0) {
    sections[activeSection - 1].scrollIntoView({ behavior: 'smooth' });
  }
}
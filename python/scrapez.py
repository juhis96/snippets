import requests
from bs4 import BeautifulSoup

# URL to scrape
base_url = "https://duunitori.fi/tyopaikat?haku=ohjelmointi+ja+ohjelmistokehitys+%28ala%29&alue=p%C3%A4%C3%A4kaupunkiseutu&filter_work_type=full_time&sivu="

print("""
 (                                  )  
 )\ )                            ( /(  
(()/(     (       )           (  )\()) 
 /(_)) (  )(   ( /(  `  )    ))\((_)\  
(_))   )\(()\  )(_)) /(/(   /((_)_((_) 
/ __| ((_)((_)((_)_ ((_)_\ (_)) |_  /  
\__ \/ _|| '_|/ _` || '_ \)/ -_) / /   
|___/\__||_|  \__,_|| .__/ \___|/___|  
                    |_|                
""")

# Send a GET request to the URL
response = requests.get(base_url+"1")

jobs_amount = 0

# Check if the request was successful
if response.status_code == 200:
    # Parse the HTML content
    soup = BeautifulSoup(response.text, 'html.parser')
    
    page_numbers = soup.find_all('a', class_='pagination__pagenum')
    
    if page_numbers:
        # Get the number from the last element
        last_page_number = int(page_numbers[-1].text.strip())
        print(f"Last Page Number: {last_page_number}\n")

        for page in range(1, last_page_number + 1):
            page_url = f"{base_url}&sivu={page}"
            response = requests.get(page_url)

            # Parse the HTML content
            soupx = BeautifulSoup(response.text, 'html.parser')

            # Find all <a> elements with the specified class
            jobs = soupx.find_all('a', class_='job-box__hover gtm-search-result')

            for job in jobs:
                # Extract the href attribute (link) from each <a> element
                job_company = job.get('data-company')
                job_name = job.text.strip()
                job_link = job.get('href')
                jobs_amount += 1

                # You can also extract other information from the job element
                # For example, job title, company, etc., depending on the HTML structure

                print(f"{job_name}, {job_company}, https://duunitori.fi{job_link}")

    print(f"Jobs available: {jobs_amount}")
else:
    print("Failed to retrieve the webpage")

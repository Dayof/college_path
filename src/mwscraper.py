import requests
from bs4 import BeautifulSoup

page_mw = requests.get('https://matriculaweb.unb.br/graduacao/fluxo.aspx?cod=1856')

courses, course, all_cred = ([], {}, [])

if page_mw.status_code == 200:
    soup = BeautifulSoup(page_mw.content, 'html.parser')
    inner_content = soup.find_all('center')

    all_a = inner_content[-1].find_all('a')

    for i in all_a:
        a_parent = i.parent
        td_parent = a_parent.parent
        last_td = td_parent.find_all('td')[-1]
        if i.text.isdigit():
            sum_cred = 0
            for cr in last_td.text.split(' - ')[:2]:
                sum_cred += int(cr)
            all_cred.append(sum_cred)

    i, j = (0, 0)
    for a in all_a:
        if a.string:
            if i%2:
                key = 'NAME'
            else:
                key = 'COD'

            course[key] = a.string.strip()
            i+=1

        if i == 2:
            course['CRED'] = all_cred[j]
            courses.append(course)
            course = {}
            i = 0
            j+=1

    print(courses)

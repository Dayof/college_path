import requests
from bs4 import BeautifulSoup

base_url = 'https://matriculaweb.unb.br'
page_mw = requests.get(base_url + '/graduacao/fluxo.aspx?cod=1856')

courses, course, all_cred, all_pr, all_courses_names = ([], {}, [], [], [])
all_refs = {}
courses_not_updated = ['COMPUTACAO BASICA']
REMOVE_OUT_FLOW = True
F = [1.0, 0.5, 0.5, 1.0, 0.5, 1.0, 0.5, 1.0, 0.5, 1.5,
    0.5, 1.0, 1.5, 1.0, 1.0, 0.5, 0.5, 1.0, 0.5, 1.0,
    1.0, 0.5, 0.5, 1.0, 1.5, 1.5, 1.5, 1.0, 0.5, 1.0,
    1.5, 1.5, 0.5, 1.5, 1.5]

def writeOnFile(prs):
    file_c = open('courses2.txt', 'w')
    org_pr = ' '.join(str(i) for i in prs)
    ord_refs = {}

    i = 0
    for i in range(len(all_pr)):
        if i not in prs.keys():
            prs[i] = '-1'
        else:
            prs[i] = ' '.join(str(i) for i in prs[i])

    for k in sorted(prs):
        ord_refs[k] = prs[k]

    i = 0
    for cr in courses:
        file_c.write(cr['COD'] + ' | ' + cr['NAME'] + ' | '
                        + str(cr['CRED']) + ' | ' + str(F[i]) + ' | '
                        + ord_refs[i] + '\n')
        print(i, cr['COD'] + ' | ' + cr['NAME'] + ' | '
                        + str(cr['CRED']) + ' | ' + str(F[i]) + ' | '
                        + ord_refs[i])
        i += 1

    file_c.close()

def addLinks(origin, refs):
    for i in refs:
        if i in all_refs.keys():
            list_on_ref = all_refs[i]
            list_on_ref.append(origin)
            all_refs[i] = list_on_ref
        else:
            all_refs[i] = [origin]

def searchRefs(list_pr):
    refs_index = []
    for pr in list_pr:
        i = 0
        for c in all_courses_names:
            if pr.strip() == c.strip():
                refs_index.append(i)
            i += 1

    if len(refs_index) != len(list_pr):
        print('Error on search references.')

    return refs_index

def beautifulName(all_pr_courses):
    result = []

    for pr in all_pr_courses:
        for c in all_courses_names:
            if c in pr.upper():
                if c.strip() == 'COMPUTACAO BASICA':
                    c = 'ALGORITMOS PROGR COMPUTADORES'
                result.append(c)

    return result

def getReq(link):
    rq_pr = requests.get(base_url + link)
    if rq_pr.status_code == 200:
        pr_soup = BeautifulSoup(rq_pr.content, 'html.parser')
        pr_req_text = pr_soup.find('b', text='Pré-req:')
        pr_td_parent = pr_req_text.parent
        pr_next_td_parent = pr_td_parent.next_sibling

        if 'Disciplina sem pré-requisitos' in pr_next_td_parent.get_text(' '):
            return None
        else:
            return pr_next_td_parent.get_text(' ')
    else:
        print('Error accessing the page %s' % rq_pr)

def separatePR(pr):
    all_pr_from_a_course, valid_pr = ([],[])

    pr = pr.split(' OU ')

    for c in pr:
        found = False
        for all_c in all_courses_names:
            if all_c in c.upper():
                found = True
        if found:
            valid_pr.append(c)
            break

    for c_pr in valid_pr:
        if ' E ' in c_pr:
            and_c = c_pr.split(' E ')

            for a_c in and_c:
                if a_c.strip() not in all_pr_from_a_course:
                    all_pr_from_a_course.append(a_c.strip())
        else:
            if c_pr.strip() not in all_pr_from_a_course:
                all_pr_from_a_course.append(c.strip())

    all_pr = beautifulName(all_pr_from_a_course)
    return all_pr

if page_mw.status_code == 200:
    soup = BeautifulSoup(page_mw.content, 'html.parser')
    inner_content = soup.find_all('center')
    all_a = inner_content[-1].find_all('a')

    for i in all_a:
        a_parent = i.parent
        td_parent = a_parent.parent
        last_td = td_parent.find_all('td')[-1]
        if i.text.isdigit():
            p_req_courses = getReq(i['href'])
            sum_cred = 0
            for cr in last_td.text.split(' - ')[:2]:
                sum_cred += int(cr)
            all_cred.append(sum_cred)
            all_pr.append(p_req_courses)

    i, j = (0, 0)

    for a in all_a:
        if a.string:
            if i%2:
                key = 'NAME'
                all_courses_names.append(a.string.strip())
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

    for c in courses_not_updated:
        all_courses_names.append(c)

    j = 0
    for i in all_pr:
        rfs, new_i = ([], [])
        if i:
            new_i = separatePR(i)
            rfs = searchRefs(new_i)
        addLinks(j, rfs)
        j += 1

    writeOnFile(all_refs)

else:
    print('Error accessing the page %s' % page_mw)

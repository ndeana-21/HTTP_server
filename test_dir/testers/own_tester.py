import requests
from requests.auth import HTTPBasicAuth

def printResponse(r):
	print("==STATUSCODE==")
	print(r.status_code)
	print("==HEADERS==")
	print(r.headers)
	print("==BODY==")
	print(r.text)
	print("******************\n")


print("GET on 9000/test")
r = requests.get('http://localhost:9000/test')
printResponse(r)

print("GET on 9000/index.html with no language parameter")
r = requests.get('http://localhost:9000/index.html')
printResponse(r)

print("GET on 9000/index.html with preferred language FR")
headers = {'Accept-Language': 'fr'}
r = requests.get('http://localhost:9000/index.html', headers=headers)
printResponse(r)

print("GET on 9000/index.html with preferred language RU")
headers = {'Accept-Language': 'ru'}
r = requests.get('http://localhost:9000/index.html', headers=headers)
printResponse(r)

print("GET on 9000/index.html with preferred language FR and preferred encoding utf8")
headers = {'Accept-Language': 'fr', 'Accept-Charset': 'utf8'}
r = requests.get('http://localhost:9000/index.html', headers=headers)
printResponse(r)

print("GET on 9000/index.html with preferred language RU and preferred encoding utf8")
headers = {'Accept-Language': 'ru', 'Accept-Charset': 'utf8'}
r = requests.get('http://localhost:9000/index.html', headers=headers)
printResponse(r)

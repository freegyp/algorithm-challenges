def safeDefine(token,num,token2num,num2token):
	if token in token2num:
		del num2token[token2num[token]]
		del token2num[token]
	if num in num2token:
		del token2num[num2token[num]]
		del num2token[num]
	token2num[token] = num
	num2token[num] = token

def calculate(tokens,token2num,num2token):
	cum,op = 0,1
	for token in tokens:
		if token=="+":
			op = 1
		elif token=="-":
			op = -1
		elif token=="=":
			if cum in num2token:
				return num2token[cum]
			return "unknown"
		elif token in token2num:
			cum += op*token2num[token]
		else:
			return "unknown"


token2num,num2token = {},{}

while True:
	try:
		s = raw_input()
	except:
		break
	if s=="clear":
		token2num,num2token = {},{}
	else:
		tokens = s.split()
		if tokens[0]=="def":
			safeDefine(tokens[1],int(tokens[2]),token2num,num2token)
		elif tokens[0]=="calc":
			res = calculate(tokens[1:],token2num,num2token)
			print " ".join(tokens[1:]+[res])
import discord as dsc
import re

from pprint import pprint
from ibm_watson import AssistantV2
from ibm_cloud_sdk_core.authenticators import IAMAuthenticator


api_key = 'ArLC9wN8GNQWiml2MS61nahxB6-RReuGSz0nFyf-c1PP'
url = 'https://api.eu-gb.assistant.watson.cloud.ibm.com/instances/bb9e27df-42fa-4f1c-bf75-e017f3899896'
assistant_id = '7509910f-dba2-43d8-80a0-049d0d504f04'
session_id = None

authenticator = IAMAuthenticator(api_key)
assistant = AssistantV2(version='2020-04-01', authenticator=authenticator)
assistant.set_service_url(url)

regex = r"\s'text': ['\"]([\w\d .:,!?\"'()@#$%&*<>]*)['\"]"


def start_session():
    global session_id
    global assistant

    if session_id:
        end_session()
    response = assistant.create_session(assistant_id=assistant_id).get_result()
    session_id = response['session_id']
    pprint(response)


def end_session():
    global session_id
    global assistant

    if not session_id:
        return
    response = assistant.delete_session(assistant_id=assistant_id, session_id=session_id).get_result()
    session_id = None
    pprint(response)


def send(text: str):
    try:
        global session_id
        global assistant_id
        global assistant
        if not session_id:
            start_session()

        input_text = {'message_type': 'text', 'text': text}

        response = assistant.message(
            assistant_id=assistant_id,
            session_id=session_id,
            input=input_text
        ).get_result()

        print(response)

        matches = re.finditer(regex, str(response), re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            for groupNum in range(0, len(match.groups())):
                groupNum = groupNum + 1

        return match.group(groupNum)

    except Exception:
        return 'Something went very wrong in my code'


start_session()

end_session()
client = dsc.Client()


@client.event
async def on_ready():
    print('Im in !!! Tonk is in!! Im {0.user} '.format(client))


@client.event
async def on_message(message):
    if message.author == client.user:
        return

    print(message.content)
    await message.channel.send(send(message.content))

client.run('ODM5NTgwNzkyNDY0MjExOTY5.YJLuiw.6YOuY9FwfpaCrLgYLuGaGYX7UEc')

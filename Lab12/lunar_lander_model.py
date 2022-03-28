import gym
import random
import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
from statistics import mean, median
from collections import Counter
from collections import deque
import matplotlib.pyplot as plt


env = gym.make('LunarLander-v2')
env.seed(0)
np.random.seed(0)

from tensorflow.compat.v1 import ConfigProto
from tensorflow.compat.v1 import InteractiveSession

def fix_gpu():
    config = ConfigProto()
    config.gpu_options.allow_growth = True
    session = InteractiveSession(config=config)

#Use the trained network saved to file
model = keras.models.load_model('lunar_model.h5')

scores = []
choices = []

print("Using the trained model ...")
for each_game in range(10):	# We will play 10 games and get the average score
    score = 0
    game_memory = []
    prev_obs = []
    env.reset()
    done = False
    while not done:
#        print("Step ", s)
        env.render()
        if len(prev_obs) == 0:
            action = random.randrange(0,2)
        else:
            temp_obs = prev_obs.reshape(-1, len(prev_obs))  # Lots of issues trying to get the shape right for the prediction
            tempaction = model(temp_obs)        # Makes a prediction
            action = np.argmax(tempaction)		# Returns the index of the max value (so either 0 or 1 which will translate to either left or right)
        choices.append(action)
        
        new_observation, reward, done, info = env.step(action)
        prev_obs = new_observation
        game_memory.append([new_observation, action])
        score += reward
    print('Done with a score of ', score)
    scores.append(score)
#print(scores)
average = sum(scores)/len(scores)
print('Average Score', average)
print("Finished")
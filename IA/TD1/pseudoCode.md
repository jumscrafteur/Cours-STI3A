## Agents fondés sur des buts
```
function Goal_Based-Agent
    state <- UPDATE-STATE(state,action,percept,model)

    if GOAL-ACHIEVED(state, goal) then 
        return a null action
    
    if plan is empty then
        plan <- PLAN(state, goal, model)
        action <- FIRST(plan)
        plan <- REST(plan)
    
    return plan
```

## Agents fondés sur l'utilité
```
function Goal_Based-Agent
    state <- UPDATE-STATE(state,action,percept,model)

    if GOAL-ACHIEVED(state, goal) then 
        return a null action
    
    if plan is empty then
        plan <- PLAN(state, utility     ,goal, model)
        action <- FIRST(plan)
        plan <- REST(plan)
    
    return plan
```
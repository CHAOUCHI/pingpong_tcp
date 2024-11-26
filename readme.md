```mermaid
flowchart
server((server))
accept["LOCK client= accept()"]
send["send(client,"ping")]
server-->socket-->bind-->listen-->accept-->send

```
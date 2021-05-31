using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveToPoint : MonoBehaviour
{
    public GameObject destination;          //obiekt do którego mamy lecieć

    Vector3 relativePosition;

    Quaternion targetRotation;

    public float rotationSpeed = 0.2f;      //prędkość obrotu
    public float movementSpeed = 2f;        // prędkość ruchu

    public float rangeMissDest = 4f;        // odległość o jaką może ominąć obiekt za którym podąża

    float rotationTime=0;

    bool rotating = false;

    public float timeBetChanges;            //czas po upływie którego zmienimy trajektorie lotu
    float counter;
    void Awake()
    {
        relativePosition = destination.transform.position;
        counter = timeBetChanges;
    }

    void Update()
    {

        if (destination)
        {
            if (counter < 0)
            {
                counter = timeBetChanges;
                relativePosition = destination.transform.position + RandomTurn() - transform.position;
                targetRotation = Quaternion.LookRotation(relativePosition);
                rotating = true;
                rotationTime = 0;
            }
            else
                counter -= Time.deltaTime;

            if (rotating)
            {
                rotationTime += Time.deltaTime * rotationSpeed;
                transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, rotationSpeed * Time.deltaTime);
                if(rotationTime > 1)
                    rotating = false;

            }

            transform.position += transform.forward * movementSpeed * Time.deltaTime;

        }
    }

    Vector3 RandomTurn()
    {
        Vector3 change;
        change = new Vector3(0, 0, 0);

        change.y = Random.Range(-rangeMissDest, rangeMissDest);
        change.x = Random.Range(-rangeMissDest, rangeMissDest);

        return change;
    }

    public void SetDestinationPoint(GameObject gameObject)  //ustawianie nowego celu
    {
        destination = gameObject;
    }
}
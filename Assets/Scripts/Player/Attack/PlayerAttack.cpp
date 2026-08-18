#include "PlayerAttack.h"
#include "Scripts/Enemy/EnemyHandler.h"

PlayerAttack::PlayerAttack()
    : m_ptr_Config(nullptr)
    , m_ptr_Player(nullptr)
    , m_ptr_Camera(nullptr)
    , m_ptr_Window(nullptr)
    , m_AttackCooldown(ATTACK_COOLDOWN)
    , m_CurrentCooldown(0.0f)
{
}

void PlayerAttack::Start(spe::EngineConfig& config, spe::Sprite* player, sf::RenderWindow* window)
{
    m_ptr_Config = &config;
    m_ptr_Player = player;
    m_ptr_Camera = config.ptr_Camera;
    m_ptr_Window = window;

    m_Potions.resize(MAX_POTIONS);
    m_PotionSprites.resize(MAX_POTIONS, nullptr);

    CreatePotionSprites();
}

void PlayerAttack::CreatePotionSprites()
{
    if (!m_ptr_Config) {
        return;
    }

    for (int i = 0; i < MAX_POTIONS; i++)
    {
        spe::Sprite* potionSprite = spe::PrefabRepository::GetPrefabByName("Potion");
        potionSprite->Transform.SetPosition(spe::Vector2(0,0));
        potionSprite->Name = "AcidPotion_" + std::to_string(i);

        // potionSprite->Tag = "Potion";
        potionSprite->SpriteRenderer.Render = false;
        potionSprite->Physicsbody.Exist = false;
        potionSprite->DontDeleteOnSceneSwap = true;

        m_ptr_Config->ptr_Sprites->Add(potionSprite);

        m_PotionSprites[i] = potionSprite;
        m_Potions[i].Init(potionSprite);
    }
}

spe::Vector2 PlayerAttack::GetMouseWorldPosition() const {
    if (!m_ptr_Window || !m_ptr_Camera) {
        return {0, 0};
    }

    // get mouse position in screen coordinates
    const sf::Vector2i mouseScreenPos = sf::Mouse::getPosition(*m_ptr_Window);

    // convert to world coordinates using the camera view
    const sf::Vector2f mouseWorldPos = m_ptr_Window->mapPixelToCoords(mouseScreenPos, m_ptr_Camera->CameraView);

    // convert to engine coordinate system
    float halfWidth = m_ptr_Window->getSize().x / 2.0f;
    float halfHeight = m_ptr_Window->getSize().y / 2.0f;

    return {mouseWorldPos.x - halfWidth, -(mouseWorldPos.y - halfHeight)};
}

int PlayerAttack::FindInactivePotion() const {
    for (int i = 0; i < MAX_POTIONS; i++)
    {
        if (!m_Potions[i].IsActive() && !m_Potions[i].IsLanded())
        {
            return i;
        }
    }
    return -1; // all potions are active
}

void PlayerAttack::Update()
{
    if (!m_ptr_Player) {
        return;
    }

    if (m_CurrentCooldown > 0)
    {
        m_CurrentCooldown -= spe::Time::s_DeltaTime;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_CurrentCooldown <= 0)
    {
        int potionIndex = FindInactivePotion();
        if (potionIndex >= 0)
        {
            spe::Vector2 playerPos = m_ptr_Player->Transform.GetPosition();
            spe::Vector2 mousePos = GetMouseWorldPosition();

            spe::Vector2 direction = mousePos - playerPos;
            if (direction.Length() > 0.001f)
            {
                direction.Normalize();
            }
            spe::Vector2 spawnPos = playerPos + direction * 30.0f;
            spawnPos.Y += 20.0f;

            m_Potions[potionIndex].Launch(spawnPos, mousePos, POTION_SPEED);
            m_CurrentCooldown = m_AttackCooldown;
        }
    }

    for (int i = 0; i < MAX_POTIONS; i++)
    {
        m_Potions[i].Update();

        if (m_Potions[i].IsActive() || m_Potions[i].IsLanded())
        {
            CheckEnemyHits();
        }
    }
}

void PlayerAttack::CheckEnemyHits()
{
    for (int i = 0; i < MAX_POTIONS; i++)
    {
        if (m_Potions[i].HasDealtDamage()) {
            continue;
        }

        if (!m_Potions[i].IsActive() && !m_Potions[i].IsLanded()) {
            continue;
        }

        spe::Sprite* potionSprite = m_Potions[i].GetSprite();
        if (!potionSprite) {
            continue;
        }

        // check collision with enemies
        spe::Sprite* hitEnemy = potionSprite->Collider.CollidedWithTag("Enemy");
        if (hitEnemy != nullptr)
        {
            EnemyHandler::GetInstance().DamageEnemyBySprite(hitEnemy, POTION_DAMAGE);
            m_Potions[i].MarkDamageDealt();

            if (m_Potions[i].IsActive())
            {
                m_Potions[i].OnLand();
            }
        }
    }
}

void PlayerAttack::OnSceneChange()
{
    // deactivate all potions when scene changes
    for (int i = 0; i < MAX_POTIONS; i++)
    {
        m_Potions[i].Deactivate();
    }
}
